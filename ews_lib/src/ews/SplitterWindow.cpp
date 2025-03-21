#include "SplitterWindow.h"

static const std::vector<luaL_Reg> methods = {
  {"EWS_SplitterWindow_Split_Horizontally", SplitterWindow::Lua_SplitHorizontally},
  {"EWS_SplitterWindow_Split_Vertically", SplitterWindow::Lua_SplitVertically},

  {"EWS_SplitterWindow_SetMinimumPaneSize", SplitterWindow::Lua_SetMinimumPaneSize},
};

ADD_FUNCS_AUTOFILL(SplitterWindow::Add_SplitterWindow_Funcs)

int SplitterWindow::Lua_Create(lua_State* L) {
  Window* parent = get_ews_object_from_top<Window>(L, 1);
  std::string name = lua_tostring(L, 2);
  std::string style = lua_tostring(L, 3);

  SplitterWindow* sw = create_new_ews_object<SplitterWindow>(L);

  sw->init(parent, name, style);

  return 1;
}

int SplitterWindow::Lua_SplitHorizontally(lua_State* L) {
  SplitterWindow* splitterwindow = get_ews_object_from_top<SplitterWindow>(L, 1);
  Window* window1 = get_ews_object_from_top<Window>(L, 2);
  Window* window2 = get_ews_object_from_top<Window>(L, 3);
  int sashposition = lua_tonumber(L, 4);

  splitterwindow->get_internal_object_type<wxSplitterWindow>()->SplitHorizontally(window1->get_internal_object_type<wxWindow>(), window2->get_internal_object_type<wxWindow>(), sashposition);

  return 0;
}

int SplitterWindow::Lua_SplitVertically(lua_State *L) {
  SplitterWindow *splitterwindow = get_ews_object_from_top<SplitterWindow>(L, 1);
  Window *window1 = get_ews_object_from_top<Window>(L, 2);
  Window *window2 = get_ews_object_from_top<Window>(L, 3);
  int sashposition = lua_tonumber(L, 4);

  splitterwindow->get_internal_object_type<wxSplitterWindow>()->SplitVertically(window1->get_internal_object_type<wxWindow>(), window2->get_internal_object_type<wxWindow>(), sashposition);

  return 0;
}

int SplitterWindow::Lua_SetMinimumPaneSize(lua_State* L) {
  auto splitterwindow = get_ews_object_from_top<SplitterWindow>(L, 1);
  auto size = lua_tonumber(L, 2);

  splitterwindow->get_internal_object_type<wxSplitterWindow>()->SetMinimumPaneSize(size);

  return 0;
}

void SplitterWindow::init(Window* parent, std::string name, std::string style) {
  this->set_internal_object_type(new wxSplitterWindow(parent->get_internal_object_type<wxWindow>(), wxID_ANY, wxDefaultPosition, wxDefaultSize, get_style_from_merged_list(style), wxString(name)));
}