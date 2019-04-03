# tscc
> Typescript to C compiler

## Support
> The compiler currently supports:

- [x] Function definitions
- [x] Data types (string, number, null, void, undefined)
- [x] Function calls
- [x] If
- [x] Else
- [X] While loops
- [x] Automatically detect requirements and inject #include tags
- [x] `==` - comparison
- [x] `!=` - comparison
- [x] `<` - comparison
- [x] `>` - comparison
- [x] Null values
- [x] Undefined values
- [x] Classes with methods
- [x] Classes with member variables
- [x] console.log

## Installation & Usage
> To install tscc, first simply compile it:
```bash
    make
```
> Then you can move it to `/usr/local/bin`:
```bash
    sudo mv ./tscc.out /usr/local/bin/tscc
```
> Now you can use it like this:
```bash
    tscc <filename>.ts
```

## Known issues
### String concatenation
> String concatenation does not work:
```typescript
    let name:string = "john " + "doe";
```

### Array initialization
> Array initialization does not work:
```typescript
    let mylist:string[] = ["john", "doe"];
```

### For loops
> For loops does not work:
```typescript
    for (let entry of someArray) {
        console.log(entry); // 1, "string", false
    }
```

### Comments
> Comments does not work:
```typescript
    // this is a comment

    /* this is also a comment */
```

### Floating point numbers
> Floating point numbers are malformed when compiled, the following code:
```typescript
    let age:number = 33.5;
```
> Becomes this when compiled (`int`):
```c
    int age = 33.5f;
```

### Interfaces
> Interfaces are currently not supported
```typescript
    interface LabeledValue {
        label: string;
        value: number;
    }
```

### Exports & Imports
> Exports and imports are currently not supported:
```typescript
    export * from "./ZipCodeValidator";  // exports class 'ZipCodeValidator

    ...

    import { ZipCodeValidator } from "./ZipCodeValidator";
```

### Too many semi colons
> The output basically looks like this right now:
```c
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
```

### Solutions
> If you find any solution for any of these issues, feel free to create a
> `pull-request`... Also if you find any other issues, please _report them_.

## Notes
### Machine code
> The compiler does _not_ turn the typescript input to machine code, you should
> use a C compiler to do that. I would suggest using `gcc`.
