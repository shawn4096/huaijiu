// Room: /data/group/leontt.c
inherit ROOM;

void create ()
{
  set ("short", "[1;31m���[1;32m ��̳[0;37;0m");
  set ("long", @LONG
  ������������̳�����湩�����ǰ���������������ƣ�
��λ��̳�������������ס��Ǳ�����Ӳ��������룬������ܻ�
����ɱ��֮����
LONG);

  set("combat_exp", 4200000);
  set("exits", ([ /* sizeof() == 1 */
  "out" : "/data/group/zongtan",
]));
  set("skill_lvl", 340);
  set("hard", 4200);
  set("objects", ([ /* sizeof() == 2 */
  "/data/group/obj/ling-pai.c" : 1,
  "/data/group/npc/hufa.c" : 2,
]));
  set("g_name", "���");

  setup();
  replace_program(ROOM);
}
