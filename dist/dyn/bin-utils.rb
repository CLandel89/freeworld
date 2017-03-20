# Helper functions for objects that have to deal with binary data.

#normal "ord" function is buggy, so...
class String
  def sord
    result = ord
    result+=0x100 if result<0
    return result
  end
end

module BinUtils
  def decode_s32 str,i
    return str[i].sord | (str[i+1].sord << 8) | (str[i+2].sord << 16) | (str[i+3].sord << 24)
  end

#  def decode_s32 str
#    decode_s32 str,0
#  end
end