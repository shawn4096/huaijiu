// Room: /data/group/rabaggio.c
inherit ROOM;

void create ()
{
  set ("short", "[1;31m���ҹ��¥[1;32m��̳����[0;37;0m");
  set ("long", @LONG
�������������ҹ��¥����̳�����������Ѿ��ķ��ˡ�
LONG);

  set("exits", ([ /* sizeof() == 1 */
  "out" : "/data/group/zongtan",
]));

  setup();
  replace_program(ROOM);
}
