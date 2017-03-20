class EntityTypeManager < Hash
  def << entityClass
    if ! entityClass.respond_to? :type_id
      puts "Fatal error: Entity class #{entityClass} does not have a method \"self.type_id\"!"
      return
    end
    type_id = entityClass.type_id
    self[type_id] = entityClass
  end
end

$entity_type_manager = EntityTypeManager.new