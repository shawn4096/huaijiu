//jiaowei qin ��β��

#include <weapon.h>
#include <ansi.h>

inherit SWORD;
inherit F_UNIQUE;

void create()
{
        set_name(HIM"��β��"NOR,({"jiaowei qin","qin", "jiaowei"}));
        set_weight(10500);
        if(clonep())
                 set_default_object(__FILE__);
        else{
              set("unit","��");
              set("value",40000);
              set("rigidity", 2);
              set("unique", 1);
              set("material","steel");
              set("long","�ഫ����ǵ�����ļ��ӻ������ȳ��Ľ�ľ���ɵ����٣��ٵ�β���Կɼ�����ɫ��\n");
              set("wield_msg",HIY"$N��������һ��,һ�Ž�β�ٱ��ѳ�����$N����.\n"NOR);
              set("unwield_msg",HIY"$Nʮָһ��������ҷȻ��ֹ��$N����β�٣��Ž����ŵİ����\n"NOR);
              }
    init_sword(65);
        setup();
}