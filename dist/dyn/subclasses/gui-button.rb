class GuiButton < GuiElement
  attr_accessor :br, :bg, :bb
  attr_accessor :dr, :dg, :db
  attr_accessor :dm, :dt

  def initialize
    super
    @hooks = Array.new
    #grey background
    self.br = self.bg = self.bb = 0x80
    #black decoration
    self.dr = self.dg = self.db = 0
    #decoration margin
    self.dm = 25
    #decoration thickness
    self.dt = 5
  end

  def draw_impl
    self.fill_rect 0,0,1,1, self.br,self.bg,self.bb
    self.decorate self.dm,self.dm,self.dm,self.dm, self.dr,self.dg,self.db, self.dt
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
