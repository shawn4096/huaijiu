
#include <ansi.h>
#include <weapon.h>
inherit HAMMER;

void create()
{
        set_name(HIY"Τ��֮��"NOR, ({ "weilan's hammer", "chui"}));
        set_weight(6000);
        if( clonep())
               set_default_object(__FILE__);
        else {
               set("unit", "��");
               set("long",@LONG
����Τ���������������ʽ�Ľ���������˹�����õ��������ɲ��ұ�С͵��ȥ��
LONG
               );
               set("value", 0);
               set("no_cun", 1);
               set("material", "steel");
               set("dazao_award",1);
               set("wield_msg", "$N����һ��$n��\n");
               set("unwield_msg", "$N�����е�$n���¡�\n");
        }
        init_hammer(20);
}