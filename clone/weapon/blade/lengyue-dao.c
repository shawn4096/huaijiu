// lengyue_dao.c ���±���
#include <ansi.h>
#include <weapon.h>
inherit BLADE;

void create()
{
        set_name( HIB"���±���"NOR , ({ "lengyue dao","blade","dao"}));
        set_weight(20000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIB"������ˮ������������ת�������������ý�˿��˿����һ��üë���¡�\n"NOR);
                set("value", 1);
                set("unique", 1);
                set("rigidity", 4);
                set("sharpness", 4);
                set("weapon_prop/parry", 4);
                set("wield_maxneili", 1400);
                set("treasure",1);
                set("wield_str", 24);
                set("material", "steel");
                set("wield_msg", HIB"$N�����鵶���ʣ���ɭɭ��һ����⼤�������գ��֮�䣬�����Ѷ���һ���������˵ĳ�����\n"NOR);
                set("unwield_msg",HIB"$N�����±���С�ĵ�����ҫ�˵ĺ���û�뵶�ʡ�\n"NOR);
        }
        init_blade(60);
        setup();
}
