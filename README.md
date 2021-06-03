## pd-memorex
[memorex ] object for Pure Data -- play back recent integer inputs.

### Description

[memorex ] records **number** input history in a memory buffer of size **size**.

There are two modes of operation controlled by the **replay** input. When **replay** is off (0), the **number** input is passed through to the output
while recording it in the memory buffer. When **replay** is on (1), the recorded **number** input history is replayed to the output using the changing
**number** input only to sequence through the buffer while ignoring its value.

The **size** input sets the size of the memory buffer. If it is positive, the buffer is FIFO (first in, first out). If negative, the buffer
is LIFO (last in, first out). Changing it erases the buffer history.

Inputs are described in the following table. All selectors can be sent as messages to the left input with arguments as specified:

| Selector   | Input  | Message argument | Effect |
|------------|--------|------------------|--------|
| **number** | left   | float (truncated to integer) | Integer input. Acts as a trigger during replay. |
| **replay** | middle | float (truncated to integer) | Send the contents of the buffer to the ouput. |
| **size**   | right  | float (truncated to integer) | Size of the buffer. If negative, replay in reverse order. Changing it erases the buffer. |

Note: the initial value of **size** can be specified within the object box itself [purdie fraction ]. Default is zero.

### Installation

The memorex.c file can be compiled into a Pure Data external using [pure-data/pd-lib-builder](https://github.com/pure-data/pd-lib-builder). Simply place the linked file (e.g. memorex.pd_linux) along with the help patch memorex-help.pd into the same directory as your patch, or somewhere on the Pd search path (e.g., externals/memorex folder).
