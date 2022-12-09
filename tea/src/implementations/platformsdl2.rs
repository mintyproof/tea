use crate::core::Platform;

pub struct PlatformSDL2 {}

impl PlatformSDL2 {
    pub fn new() -> Self {
        Self {}
    }
}

impl Platform for PlatformSDL2 {
    fn get_name(&self) -> String {
        "SDL2".to_owned()
    }

    fn runtime_milliseconds(&self) -> u64 {
        0
    }

    fn runtime_seconds(&self) -> f64 {
        0.0
    }

    fn poll_events(&mut self) {}

    fn should_quit(&self) -> bool {
        false
    }

    fn window_get_width(&self) -> u32 {
        0
    }

    fn window_get_height(&self) -> u32 {
        0
    }

    fn window_get_title(&self) -> String {
        "".to_owned()
    }

    fn window_set_size(&mut self, _: u32, _: u32) {}

    fn window_set_title(&mut self, _: &str) {}
}
