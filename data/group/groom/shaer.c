// Room: /data/group/groom/shaer.c
inherit ROOM;

void create ()
{
  set ("short", "[1;31m�ط�¥[1;32m ��̳[0;37;0m");
  set ("long", @LONG
  �������ط�¥����̳�����湩�����ǰ���������������ƣ�
��λ��̳�������������ס��Ǳ�����Ӳ��������룬������ܻ�
����ɱ��֮����
LONG);

  set("combat_exp", 5800000);
  set("g_name", "�ط�¥");
  set("exits", ([ /* sizeof() == 1 */
  "out" : "/data/group/zongtan",
]));
  set("skill_lvl", 380);
  set("objects", ([ /* sizeof() == 2 */
  "/data/group/obj/ling-pai.c" : 1,
  "/data/group/npc/hufa.c" : 2,
]));
  set("hard", 5800);

  setup();
  replace_program(ROOM);
}
