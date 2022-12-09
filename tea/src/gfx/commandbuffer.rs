use super::ColourRGB;

pub enum Command {
    SetViewport {
        x: f64,
        y: f64,
        w: f64,
        h: f64,
        depth_near: f64,
        depth_far: f64
    },
    ClearToColour(ColourRGB)
}

pub struct CommandBuffer {

}

impl CommandBuffer {

}