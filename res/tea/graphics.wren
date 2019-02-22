class Graphics {
    foreign static setTexture(tex)
    foreign static drawRectangle(x, y, w, h, color)
}

foreign class Texture {
    foreign static load(filename)

    foreign width
    foreign height
}