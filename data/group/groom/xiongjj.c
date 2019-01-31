// Room: /data/group/groom/xiongjj.c
inherit ROOM;

void create ()
{
  set ("short", "[1;31m����¥[1;32m ��̳[0;37;0m");
  set ("long", @LONG
  ����������¥����̳�����湩�����ǰ���������������ƣ�
��λ��̳�������������ס��Ǳ�����Ӳ��������룬������ܻ�
����ɱ��֮����
LONG);

  set("combat_exp", 2500000);
  set("g_name", "����¥");
  set("exits", ([ /* sizeof() == 1 */
  "out" : "/data/group/zongtan",
]));
  set("skill_lvl", 290);
  set("objects", ([ /* sizeof() == 2 */
  "/data/group/obj/ling-pai.c" : 1,
  "/data/group/npc/hufa.c" : 2,
]));
  set("hard", 2500);

  setup();
  replace_program(ROOM);
}
