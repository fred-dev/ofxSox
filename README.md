# ofxSox

openFrameworks wrapper around the [SoX](https://sourceforge.net/projects/sox/) command line tool for simple audio file processing: normalise, convert to WAV or MP3, low/high-pass filter, trim, or run any custom SoX command.

```cpp
ofxSox sox;
sox.setup();
sox.normalise("in.wav", -1.0, "out.wav");
sox.trim("out.wav", "clip.wav", 2.0, 5.5);
```

A macOS `sox` binary is included in `data/`; copy it to your app's `bin/data`, or point `soxPath` at an installed SoX. See `example/`.

Made for the Synthetic Ornithology audio pipeline (2023).
