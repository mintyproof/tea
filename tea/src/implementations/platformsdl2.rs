use crate::core::Platform;

use sdl2::{
    Sdl, TimerSubsystem, VideoSubsystem, EventPump,
    event::Event,
    keyboard::Keycode,
    video::Window
};

pub struct PlatformSDL2 {
    should_quit: bool,
    sdl: Sdl,
    timer: TimerSubsystem,
    video: VideoSubsystem,
    event_pump: EventPump,
    ticks_at_init: u64,
    performance_counter_at_init: u64,
    window: Window
}

impl PlatformSDL2 {
    pub fn new() -> Self {
        let sdl = sdl2::init().expect("failed to initialize SDL2");
        let timer = sdl.timer().expect("failed to initialize SDL2 timer subsystem");
        let video = sdl.video().expect("failed to initialize SDL2 video subsystem");
        let event_pump = sdl.event_pump().expect("failed to create SDL2 event pump");

        let ticks_at_init = timer.ticks() as u64;
        let performance_counter_at_init = timer.performance_counter();
        
        let window = video
            .window("", 800, 600)
            .position_centered()
            .opengl()
            .build()
            .expect("couldn't create window");

        Self {
            should_quit: false,
            sdl, timer, video, event_pump,
            ticks_at_init, performance_counter_at_init,
            window
        }
    }
}

impl Platform for PlatformSDL2 {
    fn get_name(&self) -> String {
        "SDL2".to_owned()
    }

    fn runtime_milliseconds(&self) -> u64 {
        self.timer.ticks() as u64 - self.ticks_at_init
    }

    fn runtime_seconds(&self) -> f64 {
        let performance_counter_now = self.timer.performance_counter();
        let frequency = self.timer.performance_frequency();
        return (performance_counter_now - self.performance_counter_at_init) as f64 / frequency as f64;
    }

    fn poll_events(&mut self) {
        for event in self.event_pump.poll_iter() {
            match event {
                Event::Quit { .. }
                | Event::KeyDown {
                    keycode: Some(Keycode::Escape),
                    ..
                } => self.should_quit = true,
                _ => {}
            }
        }
    }

    fn should_quit(&self) -> bool {
        self.should_quit
    }

    fn window_get_width(&self) -> u32 {
        self.window.size().0
    }

    fn window_get_height(&self) -> u32 {
        self.window.size().1
    }

    fn window_get_title(&self) -> String {
        self.window.title().to_owned()
    }

    fn window_set_size(&mut self, width: u32, height: u32) {
        self.window.set_size(width, height).unwrap();
    }

    fn window_set_title(&mut self, title: &str) {
        self.window.set_title(title).unwrap();
    }
}
