
template <class T>
DemoState<T>::DemoState(void)
{
}

template <class T>
DemoState<T>::DemoState(T type, renderer::Renderer* renderer, renderer::Camera*	camera) 
{
	m_type		= type;
	m_renderer	= renderer;
	m_camera	= camera;
}

template <class T>
DemoState<T>::~DemoState(void)
{
}
