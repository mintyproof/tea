pub struct ColourRGB {
    r: f64,
    g: f64,
    b: f64,
    a: f64,
}

impl ColourRGB {
    pub fn from_rgb(r: f64, g: f64, b: f64) -> Self {
        Self { r, g, b, a: 1.0 }
    }

    pub fn from_rgba(r: f64, g: f64, b: f64, a: f64) -> Self {
        Self { r, g, b, a }
    }

    pub fn from_rgb_bytes(r: u8, g: u8, b: u8) -> Self {
        Self::from_rgb(r as f64 / 255.0, g as f64 / 255.0, b as f64 / 255.0)
    }

    pub fn from_rgba_bytes(r: u8, g: u8, b: u8, a: u8) -> Self {
        Self::from_rgba(
            r as f64 / 255.0,
            g as f64 / 255.0,
            b as f64 / 255.0,
            a as f64 / 255.0,
        )
    }

    pub fn r(&self) -> f64 {
        self.r
    }

    pub fn g(&self) -> f64 {
        self.r
    }

    pub fn b(&self) -> f64 {
        self.r
    }

    pub fn a(&self) -> f64 {
        self.r
    }
}

pub mod palette {
    use super::ColourRGB;
    use lazy_static::lazy_static;

    lazy_static! {
        static ref ALICEBLUE: ColourRGB = ColourRGB::from_rgb_bytes(240, 248, 255);
        static ref ANTIQUEWHITE: ColourRGB = ColourRGB::from_rgb_bytes(250, 235, 215);
        static ref AQUA: ColourRGB = ColourRGB::from_rgb_bytes(0, 255, 255);
        static ref AQUAMARINE: ColourRGB = ColourRGB::from_rgb_bytes(127, 255, 212);
        static ref AZURE: ColourRGB = ColourRGB::from_rgb_bytes(240, 255, 255);
        static ref BEIGE: ColourRGB = ColourRGB::from_rgb_bytes(245, 245, 220);
        static ref BISQUE: ColourRGB = ColourRGB::from_rgb_bytes(255, 228, 196);
        static ref BLACK: ColourRGB = ColourRGB::from_rgb_bytes(0, 0, 0);
        static ref BLANCHEDALMOND: ColourRGB = ColourRGB::from_rgb_bytes(255, 235, 205);
        static ref BLUE: ColourRGB = ColourRGB::from_rgb_bytes(0, 0, 255);
        static ref BLUEVIOLET: ColourRGB = ColourRGB::from_rgb_bytes(138, 43, 226);
        static ref BROWN: ColourRGB = ColourRGB::from_rgb_bytes(165, 42, 42);
        static ref BURLYWOOD: ColourRGB = ColourRGB::from_rgb_bytes(222, 184, 135);
        static ref CADETBLUE: ColourRGB = ColourRGB::from_rgb_bytes(95, 158, 160);
        static ref CHARTREUSE: ColourRGB = ColourRGB::from_rgb_bytes(127, 255, 0);
        static ref CHOCOLATE: ColourRGB = ColourRGB::from_rgb_bytes(210, 105, 30);
        static ref CORAL: ColourRGB = ColourRGB::from_rgb_bytes(255, 127, 80);
        static ref CORNFLOWERBLUE: ColourRGB = ColourRGB::from_rgb_bytes(100, 149, 237);
        static ref CORNSILK: ColourRGB = ColourRGB::from_rgb_bytes(255, 248, 220);
        static ref CRIMSON: ColourRGB = ColourRGB::from_rgb_bytes(220, 20, 60);
        static ref CYAN: ColourRGB = ColourRGB::from_rgb_bytes(0, 255, 255);
        static ref DARKBLUE: ColourRGB = ColourRGB::from_rgb_bytes(0, 0, 139);
        static ref DARKCYAN: ColourRGB = ColourRGB::from_rgb_bytes(0, 139, 139);
        static ref DARKGOLDENROD: ColourRGB = ColourRGB::from_rgb_bytes(184, 134, 11);
        static ref DARKGRAY: ColourRGB = ColourRGB::from_rgb_bytes(169, 169, 169);
        static ref DARKGREEN: ColourRGB = ColourRGB::from_rgb_bytes(0, 100, 0);
        static ref DARKGREY: ColourRGB = ColourRGB::from_rgb_bytes(169, 169, 169);
        static ref DARKKHAKI: ColourRGB = ColourRGB::from_rgb_bytes(189, 183, 107);
        static ref DARKMAGENTA: ColourRGB = ColourRGB::from_rgb_bytes(139, 0, 139);
        static ref DARKOLIVEGREEN: ColourRGB = ColourRGB::from_rgb_bytes(85, 107, 47);
        static ref DARKORANGE: ColourRGB = ColourRGB::from_rgb_bytes(255, 140, 0);
        static ref DARKORCHID: ColourRGB = ColourRGB::from_rgb_bytes(153, 50, 204);
        static ref DARKRED: ColourRGB = ColourRGB::from_rgb_bytes(139, 0, 0);
        static ref DARKSALMON: ColourRGB = ColourRGB::from_rgb_bytes(233, 150, 122);
        static ref DARKSEAGREEN: ColourRGB = ColourRGB::from_rgb_bytes(143, 188, 143);
        static ref DARKSLATEBLUE: ColourRGB = ColourRGB::from_rgb_bytes(72, 61, 139);
        static ref DARKSLATEGRAY: ColourRGB = ColourRGB::from_rgb_bytes(47, 79, 79);
        static ref DARKSLATEGREY: ColourRGB = ColourRGB::from_rgb_bytes(47, 79, 79);
        static ref DARKTURQUOISE: ColourRGB = ColourRGB::from_rgb_bytes(0, 206, 209);
        static ref DARKVIOLET: ColourRGB = ColourRGB::from_rgb_bytes(148, 0, 211);
        static ref DEEPPINK: ColourRGB = ColourRGB::from_rgb_bytes(255, 20, 147);
        static ref DEEPSKYBLUE: ColourRGB = ColourRGB::from_rgb_bytes(0, 191, 255);
        static ref DIMGRAY: ColourRGB = ColourRGB::from_rgb_bytes(105, 105, 105);
        static ref DIMGREY: ColourRGB = ColourRGB::from_rgb_bytes(105, 105, 105);
        static ref DODGERBLUE: ColourRGB = ColourRGB::from_rgb_bytes(30, 144, 255);
        static ref FIREBRICK: ColourRGB = ColourRGB::from_rgb_bytes(178, 34, 34);
        static ref FLORALWHITE: ColourRGB = ColourRGB::from_rgb_bytes(255, 250, 240);
        static ref FORESTGREEN: ColourRGB = ColourRGB::from_rgb_bytes(34, 139, 34);
        static ref FUCHSIA: ColourRGB = ColourRGB::from_rgb_bytes(255, 0, 255);
        static ref GAINSBORO: ColourRGB = ColourRGB::from_rgb_bytes(220, 220, 220);
        static ref GHOSTWHITE: ColourRGB = ColourRGB::from_rgb_bytes(248, 248, 255);
        static ref GOLD: ColourRGB = ColourRGB::from_rgb_bytes(255, 215, 0);
        static ref GOLDENROD: ColourRGB = ColourRGB::from_rgb_bytes(218, 165, 32);
        static ref GRAY: ColourRGB = ColourRGB::from_rgb_bytes(128, 128, 128);
        static ref GREEN: ColourRGB = ColourRGB::from_rgb_bytes(0, 128, 0);
        static ref GREENYELLOW: ColourRGB = ColourRGB::from_rgb_bytes(173, 255, 47);
        static ref GREY: ColourRGB = ColourRGB::from_rgb_bytes(128, 128, 128);
        static ref HONEYDEW: ColourRGB = ColourRGB::from_rgb_bytes(240, 255, 240);
        static ref HOTPINK: ColourRGB = ColourRGB::from_rgb_bytes(255, 105, 180);
        static ref INDIANRED: ColourRGB = ColourRGB::from_rgb_bytes(205, 92, 92);
        static ref INDIGO: ColourRGB = ColourRGB::from_rgb_bytes(75, 0, 130);
        static ref IVORY: ColourRGB = ColourRGB::from_rgb_bytes(255, 255, 240);
        static ref KHAKI: ColourRGB = ColourRGB::from_rgb_bytes(240, 230, 140);
        static ref LAVENDER: ColourRGB = ColourRGB::from_rgb_bytes(230, 230, 250);
        static ref LAVENDERBLUSH: ColourRGB = ColourRGB::from_rgb_bytes(255, 240, 245);
        static ref LAWNGREEN: ColourRGB = ColourRGB::from_rgb_bytes(124, 252, 0);
        static ref LEMONCHIFFON: ColourRGB = ColourRGB::from_rgb_bytes(255, 250, 205);
        static ref LIGHTBLUE: ColourRGB = ColourRGB::from_rgb_bytes(173, 216, 230);
        static ref LIGHTCORAL: ColourRGB = ColourRGB::from_rgb_bytes(240, 128, 128);
        static ref LIGHTCYAN: ColourRGB = ColourRGB::from_rgb_bytes(224, 255, 255);
        static ref LIGHTGOLDENRODYELLOW: ColourRGB = ColourRGB::from_rgb_bytes(250, 250, 210);
        static ref LIGHTGRAY: ColourRGB = ColourRGB::from_rgb_bytes(211, 211, 211);
        static ref LIGHTGREEN: ColourRGB = ColourRGB::from_rgb_bytes(144, 238, 144);
        static ref LIGHTGREY: ColourRGB = ColourRGB::from_rgb_bytes(211, 211, 211);
        static ref LIGHTPINK: ColourRGB = ColourRGB::from_rgb_bytes(255, 182, 193);
        static ref LIGHTSALMON: ColourRGB = ColourRGB::from_rgb_bytes(255, 160, 122);
        static ref LIGHTSEAGREEN: ColourRGB = ColourRGB::from_rgb_bytes(32, 178, 170);
        static ref LIGHTSKYBLUE: ColourRGB = ColourRGB::from_rgb_bytes(135, 206, 250);
        static ref LIGHTSLATEGRAY: ColourRGB = ColourRGB::from_rgb_bytes(119, 136, 153);
        static ref LIGHTSLATEGREY: ColourRGB = ColourRGB::from_rgb_bytes(119, 136, 153);
        static ref LIGHTSTEELBLUE: ColourRGB = ColourRGB::from_rgb_bytes(176, 196, 222);
        static ref LIGHTYELLOW: ColourRGB = ColourRGB::from_rgb_bytes(255, 255, 224);
        static ref LIME: ColourRGB = ColourRGB::from_rgb_bytes(0, 255, 0);
        static ref LIMEGREEN: ColourRGB = ColourRGB::from_rgb_bytes(50, 205, 50);
        static ref LINEN: ColourRGB = ColourRGB::from_rgb_bytes(250, 240, 230);
        static ref MAGENTA: ColourRGB = ColourRGB::from_rgb_bytes(255, 0, 255);
        static ref MAROON: ColourRGB = ColourRGB::from_rgb_bytes(128, 0, 0);
        static ref MEDIUMAQUAMARINE: ColourRGB = ColourRGB::from_rgb_bytes(102, 205, 170);
        static ref MEDIUMBLUE: ColourRGB = ColourRGB::from_rgb_bytes(0, 0, 205);
        static ref MEDIUMORCHID: ColourRGB = ColourRGB::from_rgb_bytes(186, 85, 211);
        static ref MEDIUMPURPLE: ColourRGB = ColourRGB::from_rgb_bytes(147, 112, 219);
        static ref MEDIUMSEAGREEN: ColourRGB = ColourRGB::from_rgb_bytes(60, 179, 113);
        static ref MEDIUMSLATEBLUE: ColourRGB = ColourRGB::from_rgb_bytes(123, 104, 238);
        static ref MEDIUMSPRINGGREEN: ColourRGB = ColourRGB::from_rgb_bytes(0, 250, 154);
        static ref MEDIUMTURQUOISE: ColourRGB = ColourRGB::from_rgb_bytes(72, 209, 204);
        static ref MEDIUMVIOLETRED: ColourRGB = ColourRGB::from_rgb_bytes(199, 21, 133);
        static ref MIDNIGHTBLUE: ColourRGB = ColourRGB::from_rgb_bytes(25, 25, 112);
        static ref MINTCREAM: ColourRGB = ColourRGB::from_rgb_bytes(245, 255, 250);
        static ref MISTYROSE: ColourRGB = ColourRGB::from_rgb_bytes(255, 228, 225);
        static ref MOCCASIN: ColourRGB = ColourRGB::from_rgb_bytes(255, 228, 181);
        static ref NAVAJOWHITE: ColourRGB = ColourRGB::from_rgb_bytes(255, 222, 173);
        static ref NAVY: ColourRGB = ColourRGB::from_rgb_bytes(0, 0, 128);
        static ref OLDLACE: ColourRGB = ColourRGB::from_rgb_bytes(253, 245, 230);
        static ref OLIVE: ColourRGB = ColourRGB::from_rgb_bytes(128, 128, 0);
        static ref OLIVEDRAB: ColourRGB = ColourRGB::from_rgb_bytes(107, 142, 35);
        static ref ORANGE: ColourRGB = ColourRGB::from_rgb_bytes(255, 165, 0);
        static ref ORANGERED: ColourRGB = ColourRGB::from_rgb_bytes(255, 69, 0);
        static ref ORCHID: ColourRGB = ColourRGB::from_rgb_bytes(218, 112, 214);
        static ref PALEGOLDENROD: ColourRGB = ColourRGB::from_rgb_bytes(238, 232, 170);
        static ref PALEGREEN: ColourRGB = ColourRGB::from_rgb_bytes(152, 251, 152);
        static ref PALETURQUOISE: ColourRGB = ColourRGB::from_rgb_bytes(175, 238, 238);
        static ref PALEVIOLETRED: ColourRGB = ColourRGB::from_rgb_bytes(219, 112, 147);
        static ref PAPAYAWHIP: ColourRGB = ColourRGB::from_rgb_bytes(255, 239, 213);
        static ref PEACHPUFF: ColourRGB = ColourRGB::from_rgb_bytes(255, 218, 185);
        static ref PERU: ColourRGB = ColourRGB::from_rgb_bytes(205, 133, 63);
        static ref PINK: ColourRGB = ColourRGB::from_rgb_bytes(255, 192, 203);
        static ref PLUM: ColourRGB = ColourRGB::from_rgb_bytes(221, 160, 221);
        static ref POWDERBLUE: ColourRGB = ColourRGB::from_rgb_bytes(176, 224, 230);
        static ref PURPLE: ColourRGB = ColourRGB::from_rgb_bytes(128, 0, 128);
        static ref RED: ColourRGB = ColourRGB::from_rgb_bytes(255, 0, 0);
        static ref ROSYBROWN: ColourRGB = ColourRGB::from_rgb_bytes(188, 143, 143);
        static ref ROYALBLUE: ColourRGB = ColourRGB::from_rgb_bytes(65, 105, 225);
        static ref SADDLEBROWN: ColourRGB = ColourRGB::from_rgb_bytes(139, 69, 19);
        static ref SALMON: ColourRGB = ColourRGB::from_rgb_bytes(250, 128, 114);
        static ref SANDYBROWN: ColourRGB = ColourRGB::from_rgb_bytes(244, 164, 96);
        static ref SEAGREEN: ColourRGB = ColourRGB::from_rgb_bytes(46, 139, 87);
        static ref SEASHELL: ColourRGB = ColourRGB::from_rgb_bytes(255, 245, 238);
        static ref SIENNA: ColourRGB = ColourRGB::from_rgb_bytes(160, 82, 45);
        static ref SILVER: ColourRGB = ColourRGB::from_rgb_bytes(192, 192, 192);
        static ref SKYBLUE: ColourRGB = ColourRGB::from_rgb_bytes(135, 206, 235);
        static ref SLATEBLUE: ColourRGB = ColourRGB::from_rgb_bytes(106, 90, 205);
        static ref SLATEGRAY: ColourRGB = ColourRGB::from_rgb_bytes(112, 128, 144);
        static ref SLATEGREY: ColourRGB = ColourRGB::from_rgb_bytes(112, 128, 144);
        static ref SNOW: ColourRGB = ColourRGB::from_rgb_bytes(255, 250, 250);
        static ref SPRINGGREEN: ColourRGB = ColourRGB::from_rgb_bytes(0, 255, 127);
        static ref STEELBLUE: ColourRGB = ColourRGB::from_rgb_bytes(70, 130, 180);
        static ref TAN: ColourRGB = ColourRGB::from_rgb_bytes(210, 180, 140);
        static ref TEAL: ColourRGB = ColourRGB::from_rgb_bytes(0, 128, 128);
        static ref THISTLE: ColourRGB = ColourRGB::from_rgb_bytes(216, 191, 216);
        static ref TOMATO: ColourRGB = ColourRGB::from_rgb_bytes(255, 99, 71);
        static ref TURQUOISE: ColourRGB = ColourRGB::from_rgb_bytes(64, 224, 208);
        static ref VIOLET: ColourRGB = ColourRGB::from_rgb_bytes(238, 130, 238);
        static ref WHEAT: ColourRGB = ColourRGB::from_rgb_bytes(245, 222, 179);
        static ref WHITE: ColourRGB = ColourRGB::from_rgb_bytes(255, 255, 255);
        static ref WHITESMOKE: ColourRGB = ColourRGB::from_rgb_bytes(245, 245, 245);
        static ref YELLOW: ColourRGB = ColourRGB::from_rgb_bytes(255, 255, 0);
        static ref YELLOWGREEN: ColourRGB = ColourRGB::from_rgb_bytes(154, 205, 50);
    }
}
