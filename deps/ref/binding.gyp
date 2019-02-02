{
  'targets': [
    {
      'target_name': 'binding',
      'win_delay_load_hook': 'true',
      'sources': [ 'src/binding.cc' ],
      'include_dirs': [
        '<!(node -e "require(\'nan\')")'
      ],
    }
  ]
}
