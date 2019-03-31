#include"HuffmanTree.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	HuffmanTree ht;

	//ht.MainFromString("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed accumsan, sapien rhoncus ultricies faucibus, lectus purus lacinia metus, vitae egestas libero mauris sit amet est. Etiam quam velit, venenatis ut nibh eu, posuere consequat ex. Aenean eget lacus sapien. Nunc a magna quis urna venenatis dignissim suscipit vitae mauris. Ut sed turpis id dolor bibendum convallis eu nec magna. Vestibulum vel porta tellus. In porttitor tellus quis maximus ornare. Nam luctus placerat odio vitae placerat. Phasellus euismod sem nunc, id vehicula orci sollicitudin sed. Pellentesque sollicitudin erat nec justo malesuada dapibus.Nulla lacinia leo nec purus fermentum, ac pulvinar eros hendrerit.Proin vitae aliquam nulla, vitae ultrices risus.Mauris felis diam, finibus eu commodo at, congue vitae nisi.Sed tristique mi non diam varius, ac cursus mi volutpat.Proin porta nunc id diam sollicitudin, non porttitor elit convallis.Nulla ac lectus sit amet risus pellentesque dictum.Nulla facilisi.Nam euismod neque in leo consequat venenatis.Curabitur molestie accumsan nisi, vitae tempus quam fringilla et.Aenean massa diam, venenatis faucibus risus in, sagittis mattis ligula.Nullam elementum tincidunt accumsan.Donec tincidunt tristique ex non viverra.Fusce augue ante, tempus ac erat vel, lobortis mattis odio.Proin non auctor sapien. Quisque sed diam convallis, blandit tortor sit amet, mollis ex.Donec tincidunt dui in nisl tempor tempor in et diam.Nunc pretium eleifend orci, ut vulputate ipsum vehicula gravida.Aenean tristique scelerisque nisl, id posuere arcu feugiat et.In varius condimentum dolor.Nam euismod nunc finibus, elementum sem nec, blandit enim.Etiam luctus ultricies erat, ut tempor ex lacinia eget.Phasellus convallis sapien id nunc maximus, quis interdum massa venenatis.Vestibulum dictum imperdiet est rhoncus ultrices.Phasellus et finibus arcu, vitae aliquet mauris. Phasellus dignissim tincidunt velit, non tincidunt sem faucibus id.Maecenas fringilla sed dolor vitae suscipit.Aenean interdum tortor vel nulla accumsan vestibulum.Phasellus mauris tellus, accumsan ut odio vitae, maximus finibus turpis.Donec sagittis augue sit amet ultrices posuere.Mauris mi dolor, pretium sit amet aliquet in, imperdiet eu magna.Sed tincidunt, nisi ac facilisis rutrum, dui enim pharetra elit, quis varius leo purus sit amet massa.Nam non scelerisque neque, vel pellentesque nibh. Integer lectus turpis, posuere non tortor lacinia, tristique pellentesque odio.Suspendisse cursus diam vitae sem dignissim, id bibendum eros egestas.Cras eu volutpat orci, eu elementum risus.Integer consectetur vel mauris eget posuere.Sed pharetra augue tortor, sit amet auctor nulla malesuada aliquet.Suspendisse sed mollis risus, id ultrices ipsum. Fusce metus lacus, bibendum quis erat a, pharetra mollis diam.Nulla euismod commodo est eget consectetur.Aliquam molestie tristique ipsum, eget venenatis diam tempor vel.Integer ac diam malesuada dui laoreet accumsan ac vel mauris.Sed volutpat sit amet mi eu posuere.Proin viverra at diam a molestie.Sed ac neque malesuada, egestas elit sit amet, sagittis velit.Nullam venenatis laoreet urna, quis posuere augue vestibulum tincidunt.Donec sit amet nibh vitae nisi faucibus lacinia.Vivamus vitae egestas enim.Quisque laoreet tincidunt neque, lobortis varius mauris cursus id.Pellentesque porttitor, ligula a accumsan porttitor, nisl quam molestie lorem, ac faucibus lectus massa et neque.Suspendisse est risus, aliquet sit amet consectetur quis, lacinia et nunc.Phasellus vehicula mi orci, vitae feugiat nulla venenatis nec.");
	ht.MainFromTextFile("test.txt");

	std::cin.get();
	return 0;
}