import _ from 'fs';  // Import test
import path from 'path';


class Employee {
  fullName: string;
  constructor(public firstName: string, public lastName: string) {
    this.fullName = firstName + ' ' + lastName;
  }
  /// without public:
  /// Type 'Employee' is missing the following properties
  /// from type 'Person': firstName, lastName
  // constructor(firstName: string, lastName: string) {
  //   this.fullName = firstName + ' ' + lastName;
  // }
}

interface Person {
  firstName: string;
  lastName: string;
}

function greeting(person: Person) {
  console.log('Hello, ' + person.firstName + ' ' + person.lastName);
}

// let user = 'John';
// let user = [1, 2, 3];
// let user = { firstName: 'John', lastName: 'Doe' };
let user = new Employee('John', 'Doe');

greeting(user);
