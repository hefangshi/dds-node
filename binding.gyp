{
  'targets': [
    {
      'target_name': 'lib-dds',
      'product_prefix': 'lib',
      'type': 'static_library',
      'sources': ['lib/dds.cpp'],
    },
    {
      'target_name': 'dds',
      'sources': ['dds.cc'],
      'dependencies': [ 'lib-dds' ],
      'include_dirs': [
         'lib',
       ]
    }
  ]
}