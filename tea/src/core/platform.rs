pub trait Platform {
    /// returns a name identifying the platform.
    fn get_name(&self) -> String;

    /// returns the amount of time, in milliseconds, since the platform started. not guaranteed to start at zero.
    fn runtime_milliseconds(&self) -> u64;

    /// returns the amount of time, in seconds, since the platform started. not guaranteed to start at zero.
    fn runtime_seconds(&self) -> f64;

    /// signals the platform to process any pending unhandled events.
    fn poll_events(&mut self);

    /// returns whether the platform wants to shut down the engine and exit.  
    ///
    /// this becomes true in various circumstances- most commonly, the user clicking the close button on Tea's window.
    fn should_quit(&self) -> bool;

    /// returns the width of the window on-screen
    ///
    /// for high-DPI displays- for example, most macOS computers- this may not reflect the actual size of the drawable
    /// portion of the window; functions for determining this will be made available.. eventually.
    fn window_get_width(&self) -> u32;

    /// returns the height of the window on-screen.
    ///
    /// for high-DPI displays- for example, most macOS computers- this may not reflect the actual size of the drawable
    /// portion of the window; functions for determining this will be made available.. eventually.
    fn window_get_height(&self) -> u32;

    /// returns the title of the window.
    fn window_get_title(&self) -> String;

    /// resizes the window.
    fn window_set_size(&mut self, width: u32, height: u32);

    /// alters the title of the window.
    fn window_set_title(&mut self, title: &str);
}
