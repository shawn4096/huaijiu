// /d/wudang/yaofang.c
#include <room.h>
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short","ҩ��");
        set("long", @LONG
�����䵱ɽ���µ�һ��Сҩ����һ���䵱��ͯ���ڲ�ͣ���ŷ��䡣
���ݵ�ǽ������һ��ֽ(paper)���м���һ����¯(lu)������ɢ����Ũ
Ũ��ҩζ���ƺ������˰���ʲô��ҩ��
LONG
        );
        set("no_fight",1);
        set("objects",([
           __DIR__"danlu/lu" : 1,
           __DIR__"npc/daotong2" : 1,
         ]));
        set("exits", ([
                "east" : __DIR__"xuanyuemen",
        ]));
        set("item_desc", ([
                    "paper": "��ҩ�������£�\n"
"\n\t\t\t�� �򿪸���"HIC"<--->(open lid)\n"NOR
"\t\t\t�� ���ҩ��"HIC"<--->(add ҩ���� in lu)\n"NOR
"\t\t\t�� �����ˮ"HIC"<--->(pour ���� in lu)\n"NOR
"\t\t\t�� �رո���"HIC"<--->(close lid)\n"NOR
"\t\t\t�� ��ȼ����"HIC"<--->(dianhuo)\n"NOR
"\t\t\t�� ��ȼ���"HIC"<--->(burn coal)\n"NOR
"\t\t\t�� �尾ҩ��"HIC"<--->(aoyao)\n"NOR
"\t\t\t�� ����¯"HIC"<--->(miehuo)\n"NOR,
                         ]));

        set("coor/x",10);
  set("coor/y",30);
   set("coor/z",0);
   setup();
}
