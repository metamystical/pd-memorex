## pd-memorex
[memorex ] object for Pure Data -- play back recent integer inputs.

### Description

[memorex ] records input history in a memory buffer of size 'size'. Input can be a single integer or a list of up to eight integers, or fewer if the second object argument is set in [memorex size num_chord_notes].

There are two modes of operation controlled by the **replay** input. When **replay** is off (0), the **number** input is passed through to the output
while recording it in the memory buffer. When **replay** is on (1), the recorded **number** input history is replayed to the outputs using the changing
**number** input only as a trigger to sequence through the buffer while ignoring its value.

The **size** input sets the size of the memory buffer. If it is positive, the buffer is FIFO (first in, first out). If negative, the buffer
is LIFO (last in, first out). Changing it erases the buffer history. Its initial value can be set as the first object argumment [memorex size num_chord_notes]

Inputs are described in the following table. All selectors can be sent as messages to the left input with arguments as specified:

| Selector   | Input  | Message argument | Effect |
|------------|--------|------------------|--------|
| **number** | left   | float (truncated to integer) | Integer input. Acts as a trigger during replay. |
| **replay** | middle | float (truncated to integer) | Send the contents of the buffer to the ouput. |
| **size**   | right  | float (truncated to integer) | Size of the buffer. If negative, replay in reverse order. Changing it erases the buffer. |

Note: the initial value of **size** can be specified within the object box itself [memorex size num_chord_notes]. Default is zero.

Note: a **list** input consisting of a series of inteters following the **list** selector will be treated as a chord. All the notes of the chord will be stored in the same memory buffer location and will be output or replayed to the rightmost output as a **list** message. The first note in the chord (the first integer in the series), which may be the only non-zero note if only a single integer was input, is simultaneously sent as a float to the leftmost output.

### Installation

The memorex.c file can be compiled into a Pure Data external using [pure-data/pd-lib-builder](https://github.com/pure-data/pd-lib-builder). Simply place the linked file (e.g. memorex.pd_linux) along with the help patch memorex-help.pd into the same directory as your patch, or somewhere on the Pd search path (e.g., externals/memorex folder).
