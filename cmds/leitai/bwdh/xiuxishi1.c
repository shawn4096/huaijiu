//xiuxishi.c ��Ϣ��

#define __BWDH__ "/cmds/leitai/bwdh/"
#include <ansi.h>
#include <room.h>

inherit ROOM;
#include "pro.h"

void create()
{
        set("short",HIR"��Ϣ��"NOR);
        set("long", @LONG
�����Խ�ɽׯ����Ϣ�ң�ƽ������һƬ����֮����������ϰ������ׯ����
���ӹ̼ܽ�Ϊ�ϸ�Ҳ����Ϊ��ˣ����µ����书�󶼲���������Ʒ�ж�����
����֮��Ī����������ʱ��Ϣ����ȴ����һ�ˣ�����д��·�������һ����һ
������(sign)��
LONG
        );
        
        set("no_fight",1);
        set("item_desc",([
        	"sign" : @LONG
        	�ڱ���Ϣ�ң�����Ը����¼������飺
        	
        	һ��ȡװ��(na xxxx)��������look jia��
        	��������һ����ҶԻ�(cy xxxx)��
        	
        	������Ѿ�׼��������������(ok)���Ա㿪ʼ������\n",
LONG
        ]));
        set("objects", ([ /* sizeof() == 1 */
        	__DIR__"obj/jia" : 1,
        ]));
        setup();
}

void init()
{
	add_action("do_ok",({"done","ok"}));
	add_action("do_chuanyin",({"chuanyin","cy"}));
}
