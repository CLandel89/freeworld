class OptionManager < Hash
  def initialize
    #dummy options until they are read from the db
    self['chunk size']          = '5000'
    self['chunk min distance']  = '5000'
    self['chunk load distance'] = '10000'
    self['chunk max distance']  = '13000'
  end
end