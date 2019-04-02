# tscc
> Typescript to C compiler

## Support
> The compiler currently supports:

- [x] Function definitions
- [x] Data types (string, number, null, void, undefined)
- [x] Function calls
- [x] If
- [x] Else
- [x] Automatically detect requirements and inject #include tags
- [x] `==` - comparison
- [x] `!=` - comparison
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
    let someArray = [1, "string", false];

    for (let entry of someArray) {
        console.log(entry); // 1, "string", false
    }
```

### While loops
> While loops does not work:
```typescript
    while(condition) { 
       // statements if the condition is true 
    }
```

### Comments
> Comments does not work:
```typescript
    // this is a comment

    /* this is also a comment */
```
