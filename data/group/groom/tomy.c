// Room: /data/group/tomy.c
inherit ROOM;

void create ()
{
  set ("short", "[1;31m���ϸ��¥[1;32m ��̳[0;37;0m");
  set ("long", @LONG
  �����ǽ��ϸ��¥����̳�����湩�����ǰ���������������ƣ�
��λ��̳�������������ס��Ǳ�����Ӳ��������룬������ܻ�
����ɱ��֮����
LONG);

  set("combat_exp", 2100000);
  set("g_name", "���ϸ��¥");
  set("exits", ([ /* sizeof() == 1 */
  "out" : "/data/group/zongtan",
]));
  set("skill_lvl", 260);
  set("hard", 2100);
  set("damage", 3);
  set("objects", ([ /* sizeof() == 2 */
  "/data/group/obj/ling-pai.c" : 1,
  "/data/group/npc/hufa.c" : 2,
]));

  setup();
  replace_program(ROOM);
}
