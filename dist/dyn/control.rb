CoreUtils.add_enum 'CiType', 'enums/ci_type.enum'
CoreUtils.add_enum 'CiButton', 'enums/ci_button.enum'

class Control

  attr_reader :x, :y, :b
  attr_reader :mouse_x, :mouse_y

  def initialize player
    @player = player
    @x, @y = 0.0, 0.0
    @b = Hash.new false
    @mouse_x = 0.0
    @mouse_y = 0.0
    @hooks = Array.new
  end

  #binary helper functions
  def byteu str, b
    result = str[b].ord
    result += 0x100 if result<0
    return result
  end
  def int32 str, i
    return (byteu str,(0+i)) |
      ((byteu str,(1+i))<<8) |
      ((byteu str,(2+i))<<16) |
      ((byteu str,(3+i))<<24)
  end

  def action
    #a poll is either 8 bytes (2 variables) or empty
    while (ci = poll_ci) != '' do
      #extract the values from this control instruction
      ci_type = int32 ci,0
      ci_value = int32 ci,4
      #change exported state representation
      case ci_type
      when CiType::PRESS
        @b[ci_value] = true
      when CiType::RELEASE
        @b[ci_value] = false
      when CiType::AXIS_X
        @x = decode_f ci_value
      when CiType::AXIS_Y
        @y = decode_f ci_value
      when CiType::MOUSE
        @mouse_x = (ci_value&0xffff) / 0xffff
        @mouse_y = ((ci_value>>16)&0xffff) / 0xffff
        ci_value = [@mouse_x, @mouse_y]
      end
      #handle hooks
      @hooks.each do |hook|
        hook.control_hook ci_type, ci_value
      end
    end
  end

  def << hook
    @hooks << hook
    return self
  end

  def delete hook
    @hooks.delete hook
    return self
  end

  def decode_f num
    return num.to_f / 65536.0
  end

end

# Similar to Control, but buttons are always "false"
# and axes are always "0".
class ControlDummy
  attr_accessor :b
  def initialize
    @b = HashDummyFalse.new
  end
  def x
    return 0
  end
  def y= y
    # no-op
  end
  def y
    return 0
  end
  def y= y
    # no-op
  end
end

class HashDummyFalse
  def []=(key, value)
    # no-op
  end
  def [](key)
    return false
  end
end
