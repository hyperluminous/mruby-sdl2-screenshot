MRuby::Gem::Specification.new('mruby-sdl2-screenshot') do |spec|
  spec.license = 'MIT'
  spec.authors = 'kabies'
  spec.version = '0.1.0'

  spec.add_dependency 'mruby-sdl2'

  if not RUBY_PLATFORM.include?('darwin') and not build.kind_of?(MRuby::CrossBuild)
    spec.cc.flags << '`sdl2-config --cflags`'
    spec.linker.flags_before_libraries << '`sdl2-config --libs`'
  end
end
