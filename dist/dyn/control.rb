CoreUtils.add_enum 'CiType', 'enums/ci_type.enum'
CoreUtils.add_enum 'CiButton', 'enums/ci_button.enum'

class Control

  attr_reader :x, :y, :b

  def initialize player
    @player = player
    @x, @y = 0.0, 0.0
    @b = Hash.new false
    @hooks = Array.new
  end

  def action
    #a poll is either 8 bytes (2 variables) or empty
    while (ci = poll_ci) != '' do
      #extract the values from this control instruction
      ci_type = ci[0].ord | (ci[1].ord << 8) | (ci[2].ord << 16) | (ci[3].ord << 24)
      ci_value = ci[4].ord | (ci[5].ord << 8) | (ci[6].ord << 16) | (ci[7].ord << 24)
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
