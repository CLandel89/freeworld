module CoreUtils
  def self.finished
    return true if CoreUtils.finished_int==1
    return false
  end
end
