# Facade Pattern

“The facade pattern is a software engineering design pattern commonly used with Object-oriented programming. (The name is by analogy to an architectural facade.). A facade is an object that provides a simplified interface to a larger body of code, such as a class library.”

Façade pattern falls under the hood of **Structural Design Patterns**. Façade is nothing but an interface that hides the inside details and complexities of a system and provides a simplified front end to the client. With the façade pattern, a client can work with the interface easily and get the job done without being worried of the complex operations being done by the system

|     Facade Pattern      |
|:-----------------------:|
| ![](https://d3vv6lp55qjaqc.cloudfront.net/items/342B3v2L3q1x0F3G1t0B/Example_of_Facade_design_pattern_in_UML.png?X-CloudApp-Visitor-Id=1094421) |

```java
/* Complex parts */

class CPU {
    public void freeze() { ... }
    public void jump(long position) { ... }
    public void execute() { ... }
}

class Memory {
    public void load(long position, byte[] data) { ... }
}

class HardDrive {
    public byte[] read(long lba, int size) { ... }
}

/* Facade */

class ComputerFacade {
    private CPU processor;
    private Memory ram;
    private HardDrive hd;

    public ComputerFacade() {
        this.processor = new CPU();
        this.ram = new Memory();
        this.hd = new HardDrive();
    }

    public void start() {
        processor.freeze();
        ram.load(BOOT_ADDRESS, hd.read(BOOT_SECTOR, SECTOR_SIZE));
        processor.jump(BOOT_ADDRESS);
        processor.execute();
    }
}

/* Client */

class You {
    public static void main(String[] args) {
        ComputerFacade computer = new ComputerFacade();
        computer.start();
    }
}
```
