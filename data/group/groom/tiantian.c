// Room: /data/group/groom/tiantian.c
inherit ROOM;

void create ()
{
  set ("short", "[1;31m����[1;32m��̳����[0;37;0m");
  set ("long", @LONG
�������������õ���̳�����������Ѿ������˵����ˡ�
LONG);

  set("exits", ([ /* sizeof() == 1 */
  "out" : "/data/group/zongtan",
]));

  setup();
  replace_program(ROOM);
}
