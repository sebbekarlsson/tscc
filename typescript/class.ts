class Person {
    name: string;
    age: number;

    function constructor(name: string) {
        this.name = name;
        this.age = 10.5;
    };

    function sayName():void {
        print(this.name);
        print("\n");
    };

    function becomeOlder():void {
        this.age = this.age + 1;
    };

    function getAge():number {
        return this.age;
    };
};


function main(argc: number, argv: string[]):number {
    let person:string = new Person("John");
    person.becomeOlder();
    person.becomeOlder();
    person.becomeOlder();
    person.becomeOlder();
    person.becomeOlder();
    person.becomeOlder();
    person.becomeOlder();
    person.becomeOlder();
    person.sayName();
    person.getAge();
    console.log("This is a console.log!\n");
};
