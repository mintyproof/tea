foreign class Keyboard {
    foreign static isDown(keycode)
    foreign static isUp(keycode)
    foreign static isPressed(keycode)
    foreign static isReleased(keycode)
}

class Keys {
    // Keycodes based on GLFW keys (as of v3.2.1): 
    // https://www.glfw.org/docs/latest/group__keys.html

    static space { 32 }
    static apostrophe { 39 }
    static comma { 44 }
    static minus { 45 }
    static period { 46 }
    static slash { 47 }
    static num_0 { 48 }
    static num_1 { 49 }
    static num_2 { 50 }
    static num_3 { 51 }
    static num_4 { 52 }
    static num_5 { 53 }
    static num_6 { 54 }
    static num_7 { 55 }
    static num_8 { 56 }
    static num_9 { 57 }
    static semicolon { 59 }
    static equal { 61 }
    static a { 65 }
    static b { 66 }
    static c { 67 }
    static d { 68 }
    static e { 69 }
    static f { 70 }
    static g { 71 }
    static h { 72 }
    static i { 73 }
    static j { 74 }
    static k { 75 }
    static l { 76 }
    static m { 77 }
    static n { 78 }
    static o { 79 }
    static p { 80 }
    static q { 81 }
    static r { 82 }
    static s { 83 }
    static t { 84 }
    static u { 85 }
    static v { 86 }
    static w { 87 }
    static x { 88 }
    static y { 89 }
    static z { 90 }
    static left_bracket { 91 }
    static backslash { 92 }
    static right_bracket { 93 }
    static grave_accent { 96 }
    static world_1 { 161 }
    static world_2 { 162 }
    static escape { 256 }
    static enter { 257 }
    static tab { 258 }
    static backspace { 259 }
    static insert { 260 }
    static delete { 261 }
    static right { 262 }
    static left { 263 }
    static down { 264 }
    static up { 265 }
    static page_up { 266 }
    static page_down { 267 }
    static home { 268 }
    static end { 269 }
    static caps_lock { 280 }
    static scroll_lock { 281 }
    static num_lock { 282 }
    static print_screen { 283 }
    static pause { 284 }
    static f1 { 290 }
    static f2 { 291 }
    static f3 { 292 }
    static f4 { 293 }
    static f5 { 294 }
    static f6 { 295 }
    static f7 { 296 }
    static f8 { 297 }
    static f9 { 298 }
    static f10 { 299 }
    static f11 { 300 }
    static f12 { 301 }
    static f13 { 302 }
    static f14 { 303 }
    static f15 { 304 }
    static f16 { 305 }
    static f17 { 306 }
    static f18 { 307 }
    static f19 { 308 }
    static f20 { 309 }
    static f21 { 310 }
    static f22 { 311 }
    static f23 { 312 }
    static f24 { 313 }
    static f25 { 314 }
    static kp_0 { 320 }
    static kp_1 { 321 }
    static kp_2 { 322 }
    static kp_3 { 323 }
    static kp_4 { 324 }
    static kp_5 { 325 }
    static kp_6 { 326 }
    static kp_7 { 327 }
    static kp_8 { 328 }
    static kp_9 { 329 }
    static kp_decimal { 330 }
    static kp_divide { 331 }
    static kp_multiply { 332 }
    static kp_subtract { 333 }
    static kp_add { 334 }
    static kp_enter { 335 }
    static kp_equal { 336 }
    static left_shift { 340 }
    static left_control { 341 }
    static left_alt { 342 }
    static left_super { 343 }
    static right_shift { 344 }
    static right_control { 345 }
    static right_alt { 346 }
    static right_super { 347 }
    static menu { 348 }
}