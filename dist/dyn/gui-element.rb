class GuiElement
  attr_accessor :x,:y, :sx, :sy, :shown
  attr_accessor :children, :parent
  def initialize
    #maybe a good default, if not, inheriting classes
    #can set this after after "super"
    margin = 1/0x80
    @sx, @sy = 1-2*margin, 1-2*margin
    center
    @children = Array.new
    @shown = true
  end

  #centers self into parent, if it is not nil,
  #else into the range [0,0] to [1,1]
  def center
    if parent!=nil
      @x, @y = parent.x+parent.sx/2-@sx/2, parent.y+parent.sy/2-@sy/2
    else
      @x, @y = 0.5 - @sx/2, 0.5 - @sy/2
	end
  end

  #fill a rectangle inside (or, if you wish to, even outside)
  #of the ranges (x,y with size sx,sy) of self, e.g.
  #elem.fill_rect 0,0,1,1, 0x80,0x80,0x80 #for a grey background of elem
  def fill_rect rx,ry,rsx,rsy, r,g,b
	graphics.fill_rect_frac x+rx*sx,y+ry*sy, rsx*sx,rsy*sy, r,g,b
  end

  #draw a rectangle around self, with the given margins
  #(space from outline of self to outline of this decoration,
  #inwards, if positive) and line thickness in virtual pixels
  def decorate mt,mb,ml,mr, r,g,b, strength
    res_w = graphics.res_w
    res_h = graphics.res_h
    x_abs = x*res_w
    y_abs = y*res_h
    sx_abs = sx*res_w
    sy_abs = sy*res_h
    #borders
    bl = x_abs + ml
    br = x_abs + sx_abs - mr
    bt = y_abs + mt
    bb = y_abs + sy_abs - mb
    #lengths
    lx = br-bl
    ly = bb-bt
    #top line
    graphics.fill_rect_raw bl,         bt,         lx,      strength, r,g,b
    #bottom line
    graphics.fill_rect_raw bl,         bb-strength,lx,      strength, r,g,b
    #left line
    graphics.fill_rect_raw bl,         bt,         strength,ly,       r,g,b
    #right line
    graphics.fill_rect_raw br-strength,bt,         strength,ly,       r,g,b
  end

  def << child
    @children << child
    child.parent = self
    #scale and move child into self
    child.x *= sx
    child.x += x
    child.sx *= sx
    child.y *= sy
    child.y += y
    child.sy *= sy
    return self
  end
  def delete child
    child.sy /= sy
    child.y -= y
    child.y /= sy
    child.sx /= sx
    child.x -= x
    child.x /= sx
    child.parent = nil
    @children.delete child
    return self
  end

  def draw
    return if !self.shown
    self.draw_impl if self.respond_to? :draw_impl
    children.each do |c|
      c.draw
	end
  end

  def graphics
	return parent.graphics if parent!=nil
	return @graphics
  end
  def graphics= g
    if parent!=nil
      parent.graphics=g
	else
	  @graphics=g
	end
  end

end
