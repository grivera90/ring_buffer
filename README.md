# Ring Buffer

Implementation of a circular buffer for embedded systems.

## Description

This code is based on [AndersKaloer's repository]. What was modified as an improvement was the possibility of introducing in the buffer any type of data (void *). This way it would be open to the user to define his own data type and make use of this module.

## Getting Started

### Dependencies

* No dependencies. Standar C.
* MinGW GCC compiler.

### Use

    // define your data type. For example:
    typedef struct  __attribute__ ((__packed__))
    {
	    uint32_t can_id;
	    uint8_t payload[8];
	    uint8_t dlc;
    }can_msg_t;

    // in your app declare
    ring_buffer_t ring_buffer;
    can_msg_t mybuffer[8];
    
    // init your ring buffer
    ring_buffer_init(&ring_buffer, &mybuffer[0], sizeof(mybuffer), sizeof(can_msg_t));
    .
    .
    .

* Now you can use the function in ring_buffer.h to operate the ring buffer.

## Authors

Contributors names and contact info

* Gonzalo Rivera (collaborator)
* [AndersKaloer](https://github.com/AndersKaloer/Ring-Buffer) (Original)

## Version History

* 1.0.0
    * Initial Release

## License

* Open

## Acknowledgments

Inspiration, code snippets, etc.
* [AndersKaloer](https://github.com/AndersKaloer/Ring-Buffer)

    [AndersKaloer's repository]: <https://github.com/AndersKaloer/Ring-Buffer>