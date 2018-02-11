class GuiMenu < GuiElement

  def initialize
    super
    @selected = 0
  end

  def enter_sel
    #selected element
    se = self.children[selected]
    return if se==nil
    se.enter if se.respond_to? :enter
  end

  def selected
    @selected
  end
  def selected= s
    @selected = s
    bumped = false
    if s<0
      @selected=0
      bumped = true
    end
    l = self.children.length
    if s>=l
      @selected=l-1
      bumped = true
    end
    return @selected, bumped
  end

end

class GuiMenuV < GuiMenu
  include GuiVPanel
  def initialize
    super
  end
end
