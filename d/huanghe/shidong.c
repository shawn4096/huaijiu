// by xiaoyao

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "ʯ��");
        set("long", @LONG
����ɳĮ����Ȼ�γɵ�һ��ʯ�������й��߻谵����ȴʮ�ָ��
�������߼��ѵ��ݣ��ƺ��ǹ���˯��֮�ã��������������з·�������
ˮ��������һ�Ƿ���������ͷ��(skulls)��
LONG );
        set("exits", ([
                "out" : __DIR__"shamo1",
        ]));
        set("item_desc", ([
                "skulls" : "һ���������������ͷ����һ�������壬���಻�٣�ǡ�ǾſŰ׹�����ͷ��\n",
        ]));
        set("objects", ([
                __DIR__"npc/mei" :1,
                __DIR__"npc/chen" :1,
        ]));

        set("coor/x",100);
  set("coor/y",120);
   set("coor/z",10);
   setup();
}

void init()
{
        object me;
        me = this_player();
        if( me->query("jiuyin-xj/chenfail") > 0 ){
         me->add("jiuyin/chenfail",me->query("jiuyin-xj/chenfail"));
         me->delete("jiuyin-xj/chenfail");
        }
        if(( me->query("jiuyin/gumu")
         || me->query("jiuyin/emei"))
         && me->query("jiuyin/chenfail") >= 3){
         me->set("jiuyin/chenfail", 2);
        }
        return;
}
