// /d/mr/cufang.c
// by leontt
// update 1/5/2000

#include <ansi.h>
inherit ROOM;

void create()
{
         set("short",HIY"����"NOR);
         set("long",@long
����һ��С����, ��Ȼ����, ���ǹ���ư��, ���ν���, ������ȫ����̨
�϶��������ʹϹ��߲�, �����Ϻ, �������಻��, ��ʮ�ָɾ����롣
long);
         set("resource/water", 1);
         
         set("objects", ([
             __DIR__"obj/longjing-caiyeji" : 1,
             __DIR__"obj/feicui-yuyuan" : 1,
             __DIR__"obj/meihua-zaoya" : 1,
]));
             set("exits",([
             "east" : __DIR__"didao1",
])); 
         setup();
         
}
