{
  "targets": [
    {
      "target_name": "addon",
      "sources": [ 
        "addon.cc",
        "obj.cc"
        ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}
