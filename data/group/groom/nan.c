// Room: /data/group/nan.c
inherit ROOM;

void create()
{
  set ("short", "[1;31m�������[1;32m ��̳[0;37;0m");
  set ("long", @LONG
  ������������̵���̳�����湩�����ǰ���������������ƣ�
��λ��̳�������������ס��Ǳ�����Ӳ��������룬������ܻ�
����ɱ��֮����
LONG);

  set("skill_lvl", 250);
  set("hard", 2000);
  set("g_name", "�������");
  set("exits", ([ /* sizeof() == 1 */
"out":"/data/group/zongtan",
]));
  set("combat_exp", 2000000);
  set("objects", ([ /* sizeof() == 2 */
"/data/group/obj/ling-pai.c":1,
"/data/group/npc/hufa.c":2,
]));
  setup();
  replace_program(ROOM);
}
