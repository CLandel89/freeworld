module GuiVPanel
  attr_accessor :vp_margin
  def initialize
    super
    @vp_margin = 1/32
  end
  def vp_align_span
    # inner rectangle
    #size without margins
    swm = 1 - 2*vp_margin
    ix = self.x + self.sx*vp_margin
    isx = self.sx * swm
    iy = self.y + self.sy*vp_margin
    isy = self.sy * swm
    #span per step
    sps = isy / self.children.length
    #next rectangle (static, except for ny)
    nx = ix
    ny = iy + sps*vp_margin
    nsx = isx
    nsy = sps * swm
    self.children.each do |c|
      c.x,c.sx = nx,nsx
      c.y,c.sy = ny,nsy
      ny += sps
    end
  end
end
