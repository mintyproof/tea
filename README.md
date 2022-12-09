# tea

a cute game framework written in [rust],
allowing you to build similarly cute games with the [wren] scripting language.

if you're interested in the predecessor of this codebase from 2018 & 2019,
please see the [2018] branch.

## workspace

this is the directory structure of the various projects used to build tea:

* [gl]: bindings for opengl 3.3, generated using [gl_generator].
* [tea]: tea itself!
* [wren-bindgen]: raw rust bindings to the c version of wren, generated with [bindgen].
* [wren-rust]: a library built atop wren-bindgen, making it easier to implement rust-side.

[2018]: https://github.com/mintyproof/tea/tree/2018
[bindgen]: https://github.com/rust-lang/rust-bindgen
[gl]: gl
[gl_generator]: https://github.com/brendanzab/gl-rs/tree/master/gl_generator
[rust]: https://rust-lang.org
[tea]: tea
[tea-runner]: tea-runner
[wren]: https://wren.io
[wren-bindgen]: wren-bindgen
[wren-rust]: wren-rust