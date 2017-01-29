CoreUtils.add_enum 'CiType', 'enums/ci_type.enum'
CoreUtils.add_enum 'CiButton', 'enums/ci_button.enum'

class Control

  attr_reader :a_x, :a_y

  def initialize player
    @player = player
    @a_x, @a_y = 0.0, 0.0
    #@b = Hash.new CiType::RELEASE
    @b = Hash.new
    @b.default=CiType::RELEASE
  end

  def action
    #a poll is either 8 bytes (2 variables) or empty
    while (ci = poll_ci) != '' do
      ci_type = 0
      ci_value = 0
#      n=0; while n<4 do
#        ci_type |= ci[n].to_i << (n*8)
#        ci_value |= ci[n+4].to_i << (n*8)
#        n = n + 1
#      end
      if ci_type == CiType::PRESSED || ci_type == CiType::RELEASED
        @b[ci_value] = ci_type
      end
      if ci_type == CiType::AXIS_X
        @a_x = decode_f ci_value
      end
      if ci_type == CiType::AXIS_Y
        @a_y = decode_f ci_value
      end
    end
  end

  def decode_f num
    return (num*65536).to_i
  end

end