
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
               set("no_give", 1);
               set("no_drop", 1);
               set("no_get", "�������������뿪�Ƕ���\n");
               set("treasure",1);	
               set("degree",1);
               set("credit",60);
               set("material", "steel");
               set("dazao_award",1);
               set("wield_msg", "$N����һ��$n��\n");
               set("desc","����һ�δ�����ᡣ");
               set("unwield_msg", "$N�����е�$n���¡�\n");
        }
        init_hammer(20);
}