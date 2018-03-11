class GuiButton < GuiElement
  def initialize
    super
    @hooks = Array.new
  end

  def draw_impl
    self.fill_rect 0,0,1,1, 0x80,0x80,0x80
    dm = 25
    self.decorate dm,dm,dm,dm, 0,0,0, 5
  end

  def enter
    @hooks.each do |hook|
      if !hook.respond_to? :button_hook
        debug "#{self}: Warning: #{hook} does not respond to #{:button_hook}!"
      else
        hook.button_hook self
      end
    end
  end

  def << hook
    @hooks << hook
  end
  def delete hook
    @hooks.delete hook
  end
end
