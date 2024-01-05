# MouseInverter

## How It Works

Uses LowLevelMouseProc provided by the WINAPI to get the next mouse movement before your system can process it. That way we can calculate the mouse speed, invert it, set the Mouse Position and cancel the original movement with return -1;
- <a href="https://docs.microsoft.com/en-us/previous-versions/windows/desktop/legacy/ms644986(v=vs.85)">LowLevelMouseProc Docs</a>

## IMPORTANT!!!

- I am not responsible for your actions bla bla bla...
- CTRL+ALT+SHIFT+ESC to Exit

- ## Notes
- Originally made by user RequestFX. I just tuned the source code (with some help of stackoverflow) to accomplish the desired behavior, to tilt the movement by an arbitrary angle instead of just invert the x and y axis.  
