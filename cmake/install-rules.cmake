install(
    TARGETS compositing_exe
    RUNTIME COMPONENT compositing_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
