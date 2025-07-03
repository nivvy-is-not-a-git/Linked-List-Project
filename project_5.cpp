#include <initializer_list>
#include <iostream>
#include <cassert>

/**********************************************************************************
 * README 
 * ********************************************************************************
 * This starter code is a skeleton of the Set and Node classes.
 * You can modify this code to create your project_5 submission.
 * Any main() function or output will be ignoed by testing software.
 * A testing main() can be found on Learn.
 * 
 * From Project 5 Specification: 2.1 Development Stratigies
 * "First, implement the node class and all of its member functions. This should be
 *  straight-forward from the course notes, as they are the sam member functions as 
 *  for a linked list.
 * 
 *  Second, start with a skeleton, where each member function is defined, but where
 *  the default values of the return type is returned. ..."
 * 
 * The skeleton has been povided (below) for you to modify.
*/

class Set;
class Node;
std::ostream &operator<<( std::ostream &out, Set const &rhs );
 
  /////////////////////////////
 /// Set class declaration ///
/////////////////////////////
class Set {
  public:
    Set( std::initializer_list<int> initial_values );
   ~Set();
 
    // The instructions will describe exactly what to do
    Set( Set const &orig );
    Set( Set      &&orig );
 
    // The instructions will describe exactly what to do
    Set &operator=( Set const &orig );
    Set &operator=( Set      &&orig );
 
    // Size operations
    bool empty() const;
    std::size_t size()  const;

    // Clear all items out of the set
    void clear();
 
    // Find the value item in the set
    //  - Return the address of the node if found,
    //    and nullptr otherwise.
    Node *find( int const &item ) const;
 
    // Insert the item into the set if it
    // is not already in the set.
    //  - Return 1 if the item is new,
    //    and 0 otherwise.
    std::size_t insert( int const &item );
 
    // Insert all the items in the array
    // from array[begin] to array[end - 1]
    // that are not already in the set.
    //  - Return the number of items inserted
    //    into the set.
    std::size_t insert( int         const array[],
                        std::size_t const begin,
                        std::size_t const end );
 
    // Remove the item from the set and
    // return the number of items removed.
    std::size_t erase( int const &item );
 
    // Move any items from 'other', whose values
    // do not appear in 'this', to 'this'
    // Leave any items that already appear
    // in 'this' and 'other' in 'other'. 
    std::size_t merge( Set &other );

    void print() const;
   

 
    // Set operations
    Set &operator|=( Set const &other );
    Set &operator&=( Set const &other );
    Set &operator^=( Set const &other );
    Set &operator-=( Set const &other );
 
    Set operator|( Set const &other ) const;
    Set operator&( Set const &other ) const;
    Set operator^( Set const &other ) const;
    Set operator-( Set const &other ) const;
 
    // Returns 'true' if the 'other' set
    // is a subset of 'this' set; that is,
    // all entries in the 'other' set are
    // also in this set.
    bool operator<=( Set const &other ) const;
    bool operator>=( Set const &other ) const;
    bool operator<( Set const &other ) const;
    bool operator>( Set const &other ) const;
 
    bool operator==( Set const &other ) const;
    bool operator!=( Set const &other ) const;
   
  private:
    Node *p_head_;
 
  friend std::ostream &operator<<( std::ostream &out, Set const &rhs );
};


  ///////////////////////////////
 /// Node class declaration  ///
///////////////////////////////
class Node {
  public:
    Node( int new_value, Node *new_next );
    int   value() const;
    Node *next()  const;

  private:
    int value_;
    Node *next_;

  // Allow any member function in the class
  // 'Set' to access or modify the member
  // variables of any instance of this class.
  friend class Set;
};


 
  ///////////////////////////////
 /// Node class Definition   ///
///////////////////////////////

// Node constructor
Node::Node( int new_value, Node *new_next ) 
  : value_{new_value},next_{new_next}{}

 
int Node::value() const {
  return value_;
}

Node *Node::next() const {
  return next_;
}


  ///////////////////////////////
 /// Set class definition    ///
///////////////////////////////

// Initializing constructor
Set::Set( std::initializer_list<int> initial_values):p_head_{nullptr}{
  for (int const &value: initial_values){
    insert (value);
  }
}



// Destructor
Set::~Set() {
  clear();
}
 
// Copy constructor
Set::Set( Set const &orig ) {
  p_head_=nullptr;  
  for ( Node *ptr{ orig.p_head_ }; ptr != nullptr; ptr = ptr->next() ) {
    insert(ptr->value());
// Call 'insert(...)' with the value returned by ptr->value()
  }
}

// Move constructor
Set::Set( Set &&orig ) {
  p_head_=nullptr;
  std::swap(p_head_, orig.p_head_);
}
 
// Copy assignment
Set &Set::operator=( Set const &orig ) {
  if (this==&orig){
    return *this;
  }
  clear();
  for (Node *ptr{orig.p_head_};ptr!=nullptr;ptr=ptr->next()){
    insert (ptr->value());
  }
  return *this;
}

// Move assignment
Set &Set::operator=( Set &&orig ) {
  if (this!=&orig){
    clear();
    std::swap(p_head_,orig.p_head_);
  }
  return *this;
}


 
// Empty
bool Set::empty() const {
  if (p_head_==nullptr){
    return true;
  }
  return false;
}

// Size
size_t Set::size() const {
  std::size_t count{};
  Node* current=p_head_;
  for (count; current!=nullptr;count++){
    current=current->next();
  }
  return count;
}
 
void Set::print() const{
  Node *current =p_head_;
  while (current!=nullptr){
    std::cout<<current->value()<<"->";
    current=current->next();
  }
  std::cout<<"nullptr"<<std::endl;
}
// Clear
void Set::clear() {
  Node *current=p_head_;
  while (current!=nullptr){
    Node *temp=current;
    current=current->next();
    delete (temp); 
  }
  p_head_=nullptr;
}
 
// Find
Node *Set::find( int const &item ) const {
  Node* current=p_head_;
  while (current!=nullptr){
    if (current->value()==item){
      return current;
    }
    current=current->next();
  }  
  return nullptr;
}
 
// Insert the item into the set
std::size_t Set::insert( int const &item ) {
  if (find (item)==nullptr){
    Node* new_element=new Node (item, p_head_);
    p_head_= new_element;
    return 1;
  }
  
  return 0;
}
 
// Insert all the items in the array
std::size_t Set::insert( int const array[], std::size_t const begin, std::size_t const end ) {
  for (std::size_t i{begin};i<end;i++){
    insert (array[i]);
  }
  return 0;
}

 
// Remove the item from the set and
// return the number of items removed.
std::size_t Set::erase( int const &item ) {
  Node *prev=nullptr;
  Node *after=nullptr;
  Node *item_address=find(item);
  Node *temp=p_head_;
  if (item_address==nullptr){
    return 0;
  }
  if (temp==item_address){
    p_head_=temp->next();
    delete temp;
    return 1;
  }
  while (temp!=item_address && temp!=nullptr){
    prev=temp;
    temp=temp->next();
  }
  if (temp==item_address){
    prev->next_=temp->next();
    delete temp;
    return 1;
  }
  return 0;
}
  
// Move any items from 'other', whose values
// do not appear in 'this', to 'this'.
// Leave any items that already appear
// in both sets, in both sets. 
std::size_t Set::merge( Set &other ) {
  std::size_t count{ 0 };
  Node *current_other=other.p_head_;
  Node *prev_other=nullptr;
  while (current_other!=nullptr){
    if (find(current_other->value())==nullptr){
      //Remove node from other
      if (prev_other==nullptr){
        other.p_head_=current_other->next(); //If first node
      }
      else{
        prev_other->next_=current_other->next(); //Otherwise skip first node
      }
      //Move node to this

      Node *to_move=current_other;
      current_other=current_other->next();//Move node to next one in other

      to_move->next_=p_head_;
      p_head_=to_move;
      count++;
      
    }
    else{
      prev_other=current_other;
      current_other=current_other->next();
    }
  }  
  
  return count;
}

  //////////////////////
 /// Set operations ///
//////////////////////
Set &Set::operator|=( Set const &other ) {
  Node *current=other.p_head_;
  while (current!=nullptr){
    insert (current->value());
    current=current->next();
  }
  return *this;
}
 
Set &Set::operator&=( Set const &other ) {
  Node *current=p_head_;
  while (current!=nullptr){
    Node *next=current->next();
    if (other.find (current->value())==nullptr){
      erase (current->value());
    }
    current=next;
  }
  return *this;
}
 
Set &Set::operator^=( Set const &other ) {
  Node *current=other.p_head_;
  while (current!=nullptr){
    if (find (current->value())!=nullptr){
      erase (current->value());
    }
    else{
      insert (current->value());
    }
    current=current->next();
  }   
  return *this;
}
 
Set &Set::operator-=( Set const &other ) {
  Node *current=other.p_head_;
  while (current!=nullptr){
    if (find(current->value())!=nullptr){
      erase (current->value());
    }
    current=current->next();
  }
  return *this;
}
 
Set Set::operator|( Set const &other ) const {
  Set result{};
  return result;
}
 
Set Set::operator&( Set const &other ) const {
  Set result{};
  return result;
}
 
Set Set::operator^( Set const &other ) const {
  Set result=*this;
  result^=other;
  return result;
}
 
Set Set::operator-( Set const &other ) const {
  Set result=*this;
  result-=other;
  return result;
}
 
// Returns 'true' if the 'other' set
// is a subset of 'this' set; that is,
// all entries in the 'other' set are
// also in this set.
bool Set::operator>=( Set const &other ) const {
  bool is_super_set=false;
  Node *current=other.p_head_;
  while (current!=nullptr){
    if (find (current->value())==nullptr){
      return false;
    }
    current=current->next();
  }
  return true;
}
 
bool Set::operator<=( Set const &other ) const {
  return (other>=*this);
}
 
bool Set::operator>( Set const &other ) const {
  bool is_super_set=false;
  if ((*this>=other)==true){
    if (this->size()==other.size()){
      is_super_set=false;
    }
    else{
      is_super_set=true;
    }
  }
  return is_super_set;
}
 
bool Set::operator<( Set const &other ) const {
  return (other>*this);
}
 
bool Set::operator==( Set const &other ) const {
  if ((*this>=other)==true && this->size()==other.size()){
    return true;
  }
  return false;
}
 
bool Set::operator!=( Set const &other ) const {
  if ((*this==other)==false){
    return true;
  }
  return false;
}


  ////////////////////////////////////////////
 /// Supplied Code for print Set objects  ///
////////////////////////////////////////////
/// @brief Overloads the << operator allowing the print of Set objects
/// @param out The ostream to print to (e.g. std::cout <<)
/// @param rhs The Set to print (e.g. << set_A)
/// @note You do not need to edit or alter this code
std::ostream &operator<<( std::ostream &out, Set const &rhs ) {
  out << "{";
  if ( !rhs.empty() ) {
    out << rhs.p_head_->value();   
    for ( Node *ptr{ rhs.p_head_->next() }; ptr != nullptr; ptr = ptr->next() ) {
      out << ", " << ptr->value();
    }
  }
  out << "}";
 
  return out;
}