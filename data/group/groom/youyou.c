// Room: /data/group/youyou.c
inherit ROOM;

void create ()
{
  set ("short", "[1;31m���Ʒ�����[1;32m ��̳[0;37;0m");
  set ("long", @LONG
  ���������Ʒ����˵���̳�����湩�����ǰ���������������ƣ�
��λ��̳�������������ס��Ǳ�����Ӳ��������룬������ܻ�
����ɱ��֮����
LONG);

  set("combat_exp", 4500000);
  set("exits", ([ /* sizeof() == 1 */
  "out" : "/data/group/zongtan",
]));
  set("skill_lvl", 350);
  set("hard", 4500);
  set("objects", ([ /* sizeof() == 2 */
  "/data/group/obj/ling-pai.c" : 1,
  "/data/group/npc/hufa.c" : 2,
]));
  set("g_name", "���Ʒ�����");

  setup();
  replace_program(ROOM);
}
