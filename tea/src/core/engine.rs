use super::Platform;
use crate::gfx::Renderer;

type PlatformRef<'a> = &'a mut (dyn Platform + 'a);
type RendererRef<'a> = &'a mut (dyn Renderer + 'a);

pub struct Engine {
    platform: Box<dyn Platform>,
    renderer: Box<dyn Renderer>,
}

impl Engine {
    pub fn new(platform: Box<dyn Platform>, renderer: Box<dyn Renderer>) -> Self {
        Self { platform, renderer }
    }

    pub fn platform(&self) -> &dyn Platform {
        &*self.platform
    }

    pub fn platform_mut(&mut self) -> &mut dyn Platform {
        &mut *self.platform
    }

    pub fn renderer(&self) -> &dyn Renderer {
        &*self.renderer
    }

    pub fn renderer_mut(&mut self) -> &mut dyn Renderer {
        &mut *self.renderer
    }
}
