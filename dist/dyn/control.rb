CoreUtils.add_enum 'CiType', 'enums/ci_type.enum'
CoreUtils.add_enum 'CiButton', 'enums/ci_button.enum'

class Control

  attr_reader :x, :y, :b

  def initialize player
    @player = player
    @x, @y = 0.0, 0.0
    @b = Hash.new false
  end

  def action
    #a poll is either 8 bytes (2 variables) or empty
    while (ci = poll_ci) != '' do
      ci_type = ci[0].ord | (ci[1].ord << 8) | (ci[2].ord << 16) | (ci[3].ord << 24)
      ci_value = ci[4].ord | (ci[5].ord << 8) | (ci[6].ord << 16) | (ci[7].ord << 24)
      case ci_type
      when CiType::PRESS
        @b[ci_value] = true
      when CiType::RELEASE
        @b[ci_value] = false
      when CiType::AXIS_X
        @x = decode_f ci_value
      when CiType::AXIS_Y
        @y = decode_f ci_value
      end
    end
  end

  def decode_f num
    return num.to_f / 65536.0
  end

end
